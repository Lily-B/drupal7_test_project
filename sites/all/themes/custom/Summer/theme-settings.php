<?php
/**
 * Created by PhpStorm.
 * User: root
 * Date: 22.09.16
 * Time: 12:23
 */
function summer_form_system_theme_settings_alter(&$form, $form_state) {
  $form['theme_settings']['footer_text'] = array(
    '#title' => t('Footer text'),
    '#type' => 'checkbox',
    '#default_value' => theme_get_setting('footer_text'),
    '#description' => t("Shows footer text in footer"),
  );
}