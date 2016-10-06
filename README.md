# DKAN Metadata Source

This module creates a ``Metadata Source`` content type and ``Metadata Type`` taxonomy term.

The ``Metadata Source`` allows DKAN Datasets to be linked to metadata sources that are either uploaded to or linked to.

This is useful for including metadata that is created outside of DKAN and would be onerous to import with a 1 to 1 field ratio in DKAN Dataset.

The ISO 19115 metadata specification for example has dozens of fields that are often created with other systems such as GeoNetwork.

## Installation
Install like any other Drupal module. Once enabled you will have the new content type and taxonomy term.

## Creating a ``Metadata Type``

The ``Metadata Type`` is a taxonomy term used for linking multiple metadata sources with the same specification. To add or remove ``Metadata Types`` visit ``l/admin/structure/taxonomy/extended_metadata_schema``.

Click ``Add term`` to create a new type or ``edit`` on an existing type to update or change.

## Creating a ``Metadata Source``

To create a new ``Metadata Type`` visit ``node/add/metadata``:

<img width="1180" alt="metadata content type form" src="https://cloud.githubusercontent.com/assets/512243/9552367/0927b9d2-4d7d-11e5-85e6-137751a336b1.png">

## Link on Dataset
Once a ``Metadata Type`` has been created the Metadata Source will be displayed on the linked ``Datasets``:

<img width="446" alt="Metadata Source on node view" src="https://cloud.githubusercontent.com/assets/512243/9552388/3d15af2e-4d7d-11e5-9d51-2304bf03c59f.png">

## JSON Schema Support

### Rendering
TODO
