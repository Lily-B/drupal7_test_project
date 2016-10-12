/**
 * Created by root on 07.10.16.
 */

(function ($) {
    Drupal.behaviors.petsOwnersStorageBehavior = {
        attach: function (context, settings) {

            setInterval(sendRequest, 3000);

            function sendRequest() {
                var settings = {url : 'pets_owners_storage_colors'};
                var ajax = new Drupal.ajax(false, '', settings );
                ajax.eventResponse(ajax, {});
            }
        }
    };
    Drupal.ajax.prototype.commands.new_color = function(ajax, response, status) {
        $('div.tabs ul.primary li a').css({'background-color': response.color});
    }
})(jQuery);