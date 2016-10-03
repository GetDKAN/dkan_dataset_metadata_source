<?php
/**
 * @file
 * Theme functions for metadata sources.
 */

/**
 * Implements hook_theme().
 */
function dkan_dataset_metadata_source_theme() {
  $theme = array(
    'dkan_dataset_metadata_source_view' => array(
      'variables' => array('node' => NULL),
    ),
    'json_schema' => array(
      'variables' => array(
        'json_array' => NULL,
        'jsonSchema_array' => NULL,
      ),
    ),
  );
  return $theme;
}

/**
 * Output the resource into the node content.
 *
 * @todo  Put CSS in separate file!
 */
function theme_dkan_dataset_metadata_source_view($vars) {
  $output = '<h2>' . t('Metadata Source') . '</h2>';
  $node = entity_metadata_wrapper('node', $vars['node']);
  $sources = $node->field_metadata_sources->value();
  $links = array();
  // @todo dkat markup?
  $output .= '<div property="dcat:distribution">';
  if (isset($sources)) {
    if (is_object($sources)) {
      $sources = array($sources);
    }
    foreach ($sources as $metadata_source) {
      // Node could be empty if it has been deleted.
      if (!$node) {
        continue;
      }
      $metadata_source_wrapper = entity_metadata_wrapper('node', $metadata_source);
      $type = 'data';
      if (isset($metadata_source->field_metadata_file['und'][0]['filemime'])) {
        $filemime = $metadata_source->field_metadata_file['und'][0]['filemime'];
        $type = recline_get_data_type($filemime);
      }
      $icon = '<span data-toggle="tooltip" class="format-label" property="dc:format" data-original-title="' . $type . '" data-format="' . $type. '">' . $type  . '</span>';


      if (isset($metadata_source->field_metadata_schema) && $metadata_source->field_metadata_schema && $metadata_source_wrapper->field_metadata_schema->value()) {
        $title = t("@type Metadata", array("@type" => $metadata_source_wrapper->field_metadata_schema->value()->name));
      }
      else {
        $title = t("%type Metadata", array("%type" => $metadata_source_wrapper->title->value()));
      }
      $view_url = NULL;
      $view_link = '';
      if (isset($metadata_source->field_metadata_view[LANGUAGE_NONE])) {
        $view_url = $metadata_source->field_metadata_view[LANGUAGE_NONE][0]['url'];
        $view_link = l(
          t('View Metadata'),
          $view_url,
          array(
            'attributes' => array(
              'class' => array(
                'btn',
                'btn-primary',
              ),
            ),
          )
        );
        $title = l($title, $view_url, array(
          'html' => TRUE,
          'attributes' => array(
            'class' => array('heading'),
            'title' => $metadata_source->title,
            'property' => 'dcat:accessURL',
          ))
        );
      }
      $download_link = '';
      if (isset($metadata_source->field_metadata_file[LANGUAGE_NONE])) {
        $url = file_create_url($metadata_source->field_metadata_file[LANGUAGE_NONE][0]['uri']);
        $download_link = l(
          '<i class="fa fa-download"></i>',
          $url,
          array(
            'html' => TRUE,
            'attributes' => array(
              'class' => array('btn', 'btn-primary'),
            ),
          )
        );
      }
      $dcat = '<div class="metadata-source">';
      $contextual = '';
      // Haven't been able to make contextual links work the right way, hardcoding
      // and checking access manually
      if (node_access('update', $metadata_source)) {
        $edit_link = l(t('Edit source'), 'node/' . $metadata_source->nid . '/edit', array('query' => array('destination' => 'node/' . $node->getIdentifier())));
        $contextual = '<div style="position:relative; float:right" class="contextual-links-wrapper"><ul class="contextual-links"><li class="0 first last"><li>' . $edit_link . '</li></ul></div>';
      }
      $links[] = $dcat . $contextual . $title . $icon . '<span class="links">' . $view_link . $download_link . '</span></div>';
    }
    $output .= theme('item_list', array('items' => $links, 'attributes' => array('class' => array('metadata-source-list'))));
    // Close first dcat declaration.
    $output .= '</div>';
  }
  if (!empty($links)) {
    return $output;
  }
  else {
    return '';
  }
}

/**
 * @vars expected variables:
 * - json_array
 * - jsonSchema_array
 */
function theme_json_schema($vars) {
  $json_array = $vars['json_array'];
  $jsonSchema_array = $vars['jsonSchema_array'];

  //Get the jsonSchema id
  $jsonSchema_id = $jsonSchema_array['id'];
  $jsonSchema_id = preg_replace('@[^a-z0-9-]+@', '_', strtolower($jsonSchema_id));

  // Get array of available theme hooks.
  $theme_hooks = theme_get_registry(TRUE);
  $theme_hooks = array_map(function ($theme_hook) {
    return isset($theme_hook['function']) ? $theme_hook['function'] : FALSE;;
    }, $theme_hooks
  );
  $theme_hooks = array_filter($theme_hooks);

  // Is there any theme that wants to take over this particular jsonSchema?
  // Lookup the theme registry for any.
  $theme_hook_grep = '@^' . 'theme_(.*)_' . $jsonSchema_id . '$@';
  $theme_hooks_matched = preg_grep($theme_hook_grep, $theme_hooks);
  if (!empty($theme_hooks_matched)) {
    // We found a theme function that overrides the passed jsonSchema.
    $theme_hook_selected = array_pop($theme_hooks_matched);
    return call_user_func($theme_hook_selected, $vars);
  }

  // We will need the properties array a lot.
  $jsonSchema_properties = $jsonSchema_array['properties'];

  // Construct rows from json data and the associated jsonSchema.
  $rows = array();
  foreach ($json_array as $property_name => $property_value) {
    $row = array();
    $property_info = $jsonSchema_properties[$property_name];
    $row[] = array(
      'header' => TRUE,
      'data' => $property_info['title'],
    );

    // Is there any theme that wants to take over this particular jsonSchema property?
    // Lookup the theme registry for any.
    $theme_hook_grep = '@^' . 'theme_(.*)_' . $jsonSchema_id . '_' . $property_name . '$@';
    $theme_hooks_matched = preg_grep($theme_hook_grep, $theme_hooks);
    // Use property specific theme if any.
    if (!empty($theme_hooks_matched)) {
      // We found a theme function that overrides the passed jsonSchema.
      $theme_hook_selected = array_pop($theme_hooks_matched);
      $row[] = call_user_func($theme_hook_selected, $vars);
    }
    else {
      $row[] = $property_value;
    }

    $rows[] = $row;
  }

  $metadata_source_json = array(
    '#theme' => 'table',
    '#header' => array(),
    '#rows' => $rows,
    '#attributes' => array(
      'class' => array(
        'test-class',
      ),
    )
  );

  return drupal_render($metadata_source_json);
}
