(function ($) {

  Drupal.behaviors.dkanDatasetMetaSource = {
    attach: function (context, settings) {
      var height = 150;
      var offset = height - 20;
      // Adds "Show more" to rows longer than height.
      $('#edit-field-metadata-file a.filefield-source-remotefile').click(function(e) {
        $('input[name="field_metadata_file_und_0_upload_button"]').hide();
      });
      $('#edit-field-metadata-file a.filefield-source-upload').click(function(e) {
        $('input[name="field_metadata_file_und_0_upload_button"]').show();
      });
    }
  }

})(jQuery);
