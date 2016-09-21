<?php
/**
 * @file
 * dkan_dataset_metadata_source.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dkan_dataset_metadata_source_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function dkan_dataset_metadata_source_node_info() {
  $items = array(
    'metadata' => array(
      'name' => t('Metadata Source'),
      'base' => 'node_content',
      'description' => t('A file or external resource with extended metadata for the dataset.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('Give metadata sources specific, descriptive titles such as "ISO-19139 Metadata" or "Original FGDC Metadata"'),
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
