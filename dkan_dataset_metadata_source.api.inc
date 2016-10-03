<?php

/**
 * @file
 * dkan_dataset_metadata_source.api.inc.
 */

/**
 * Defines location for taxonomy source file.
 *
 * @return array
 * Return an array with the following keys:
 * - taxonomy_machine_name
 *   Machine name for taxonomy you are creating.
 *   - export_path
 *     Location of json file with vocabulary terms. Should be an array of key
 *     value pairs:
 *     [
 *       {
 *         "name":"Term 1",
 *         "weight":"0",
 *       },
 *       {
 *         "name":"Term 2",
 *         "weight":"0",
 *       }
 *     ]
 *   - map
 *      Map of keys from json file. See example below.
 *
 */
function hook_metadata_taxonomy_sources() {
  $module_path = drupal_get_path('module', 'my_module');
  $map =  array(
    'name' => 'name',
    'weight' => 'weight',
  );
  return array(
    'taxonomy_machine_name' => array(
      'export_path' => $module_path . '/data',
      'map' => $map,
    ),
  );
}

/**
 * Theme function to override the display of the json-schema with id
 * "wbddh.com/geospatial_schema", all the special characters are replaced with
 * underscores.
 */
function theme_dkan_dataset_metadata_source_wbddh_com_geospatial_schema($vars) {
  return '<div>' . "Return HTML override the entire json-schema here." . '<\div>';
}

/**
 * Theme function to override the display of the json-schema property named
 * "mapProject" within the schema id "wbddh.com/geospatial_schema", all the
 * special characters are replaced with underscores.
 */
function dkan_dataset_metadata_source_wbddh_com_geospatial_schema_mapProject($vars) {
  return '<div>' . "Return HTML override for the json-schema property here." . '<\div>';
}
