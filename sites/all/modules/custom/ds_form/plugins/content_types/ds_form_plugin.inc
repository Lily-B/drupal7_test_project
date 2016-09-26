<?php
$plugin = array(
  'title' => t('DS form plugin'), // Название плагина, отображаемое при его выборе.
  'description' => t('Descriiiption.'), // Описание плагина, отображаемое при его выборе.
  'render callback' => 'ds_form_content_type_render', // Функция, которая будет формировать и выводить содержимое плагина.
//  'edit form' => 'ds_edit_form', // Форма с настройками плагина.
  'category' => t('Custom panes'), // Категория, в которой будет находиться плагин.
  'single' => TRUE, // Флаг, указывающий является ли плагин подтипом другого.
);

/**
 * 'Edit form' callback for the content type.
 */
//function ds_edit_form($form, &$form_state) {
//  // Получаем ранее введенные настройки.
//  $conf = $form_state['conf'];
//
//  $form['text'] = array(
//    '#type' => 'textarea',
//    '#title' => t('Custom text'),
//    '#default_value' => !empty($conf['text']) ? $conf['text'] : '',
//  );
//
//  return $form;
//}
//
///**
// * Submit callback for the example_text_edit_form().
// */
//function ds_edit_form_submit($form, &$form_state) {
//  // Сохраняем настройки.
//  $form_state['conf'] = array(
//    'text' => $form_state['values']['text'],
//  );
//}

/**
 * Render callback for the content type.
 */
function ds_form_content_type_render($subtype, $conf, $args, $context) {
  $form = new stdClass();
  $form ->content = drupal_get_form('ds_form_subscription_form');
  return $form;
}


