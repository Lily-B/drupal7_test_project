<?php
$plugin = array(
  'title' => t('DS form plugin'), // Название плагина, отображаемое при его выборе.
  'description' => t('News subscription form.'), // Описание плагина, отображаемое при его выборе.
  'render callback' => 'ds_form_content_type_render', // Функция, которая будет формировать и выводить содержимое плагина.
  'category' => t('Custom panes'), // Категория, в которой будет находиться плагин.
  'single' => TRUE, // Флаг, указывающий является ли плагин подтипом другого.
);

/**
 * Render callback for the content type.
 */
function ds_form_content_type_render($subtype, $conf, $args, $context) {
  $form = new stdClass();
  $form ->content = drupal_get_form('ds_form_subscription_form');
  return $form;
}


