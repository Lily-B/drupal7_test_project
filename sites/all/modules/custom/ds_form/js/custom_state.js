/**
 * Support post-install task forms.
 */

/**
 * Adds custom state for adding a *in the end of place placeholder (placeholder <- input label)
 */
(function ($) {
    $(document).bind('state:custom_state', function (e) {

        if (e.trigger) {
            if (e.value) {

                var required_placeholder = e.target.labels["0"].innerHTML.concat('*');
                $(e.target).attr('placeholder', required_placeholder);
            }
            else{
                var required_placeholder = e.target.labels["0"].innerHTML;
                $(e.target).attr('placeholder', required_placeholder);
            }
        }
    });
})(jQuery);