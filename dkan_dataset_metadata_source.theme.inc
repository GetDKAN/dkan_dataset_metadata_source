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

      if (isset($metadata_source->field_metadata_schema) && $metadata_source->field_metadata_schema && $metadata_source_wrapper->field_metadata_schema->value()) {
        $term .= '<span class="format-label" property="dc:format" data-format="' . $metadata_source_wrapper->field_metadata_schema->value()->name . '">' . $metadata_source_wrapper->field_metadata_schema->value()->name  . '</span>';
      }
      else {
        $term = '<span class="format-label" property="dc:format" data-format="data">Metadata</span>';
      }
      $view_url = NULL;
      $view_link = '';
      $title = $metadata_source_wrapper->title->value();
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
        $title = l($metadata_source_wrapper->title->value(), $view_url, array(
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
      $links[] = $dcat . $contextual . $title . $term . $desc . '<span class="links">' . $view_link . $download_link . '</span></div>';
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

