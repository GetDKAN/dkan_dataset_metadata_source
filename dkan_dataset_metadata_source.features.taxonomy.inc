<?php
/**
 * @file
 * dkan_dataset_metadata_source.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function dkan_dataset_metadata_source_taxonomy_default_vocabularies() {
  return array(
    'extended_metadata_schema' => array(
      'name' => 'Extended Metadata Schema',
      'machine_name' => 'extended_metadata_schema',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
