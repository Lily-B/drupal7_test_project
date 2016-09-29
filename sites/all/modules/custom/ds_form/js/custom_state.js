/**
 * Support post-install task forms.
 */

/**
 * Adds custom state for adding a *in the end of place placeholder (placeholder <- input label)
 */
(function ($) {
    $(document).bind('state:custom_state', function (e) {

        if (e.trigger) {
            var placeholder = $(e.target).attr('placeholder').replace(/\*+$/g, '');
            // var placeholder = $(e.target).attr('placeholder').replace(/[^a-zA-Z ]/g, '');
            if (e.value) {
                var required_placeholder = placeholder.concat('*');
                $(e.target).attr('placeholder', required_placeholder);
            }
            else{
                $(e.target).attr('placeholder', placeholder);
            }
        }
    });
})(jQuery);

