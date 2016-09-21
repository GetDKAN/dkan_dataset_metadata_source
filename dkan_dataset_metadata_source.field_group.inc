<?php
/**
 * @file
 * dkan_dataset_metadata_source.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function dkan_dataset_metadata_source_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata_file|node|metadata|form';
  $field_group->group_name = 'group_metadata_file';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'metadata';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_metadata_type';
  $field_group->data = array(
    'label' => 'Add Metadata',
    'weight' => '11',
    'children' => array(
      0 => 'field_metadata_json',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Add Metadata',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-metadata-file field-group-htab',
        'description' => 'Create new metadata file.',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_metadata_file|node|metadata|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata_json_schema|node|metadata|form';
  $field_group->group_name = 'group_metadata_json_schema';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'metadata';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_metadata_type';
  $field_group->data = array(
    'label' => 'Metadata JSON Schema',
    'weight' => '10',
    'children' => array(),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Metadata JSON Schema',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => 'json-schema',
        'classes' => 'group-metadata-json-schema field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_metadata_json_schema|node|metadata|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata_link|node|metadata|form';
  $field_group->group_name = 'group_metadata_link';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'metadata';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_metadata_type';
  $field_group->data = array(
    'label' => 'Link Metadata',
    'weight' => '12',
    'children' => array(
      0 => 'field_metadata_file',
      1 => 'field_metadata_view',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Link Metadata',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-metadata-link field-group-htab',
        'description' => 'Link to or upload an existing metadata file.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_metadata_link|node|metadata|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata_type|node|metadata|form';
  $field_group->group_name = 'group_metadata_type';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'metadata';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata Type',
    'weight' => '2',
    'children' => array(
      0 => 'group_metadata_json_schema',
      1 => 'group_metadata_file',
      2 => 'group_metadata_link',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Metadata Type',
      'instance_settings' => array(
        'id' => 'metadata-type',
        'classes' => 'group-metadata-type field-group-htabs',
      ),
    ),
  );
  $field_groups['group_metadata_type|node|metadata|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Add Metadata');
  t('Link Metadata');
  t('Metadata JSON Schema');
  t('Metadata Type');

  return $field_groups;
}
