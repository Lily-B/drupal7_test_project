<?php

/**
 * Custom Pets owner's form.
 */
function batch_change_name_form($form, &$form_state) {

  $form['p_o'] = [
    '#type' => 'fieldset',
    '#title' => t('Change names'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['p_o']['old_name'] = [
    '#prefix' => '<div id="oldName">',
    '#suffix' => '</div>',
    '#title' => t('Old Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => [
      'placeholder' => t('Old Name '),
    ],
    '#size' => 20,
    '#maxlength' => 20,
    '#rules' => [
      'alpha_dash',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      ],
    ],
  ];
  $form['p_o']['new_name'] = [
    '#prefix' => '<div id="newName">',
    '#suffix' => '</div>',
    '#title' => t('New Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => [
      'placeholder' => t('New Name '),
    ],
    '#size' => 20,
    '#maxlength' => 20,
    '#rules' => [
      'alpha_dash',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      ],
    ],
  ];
  $form['p_o']['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Change!'),
  );
  return $form;
}




/**
 * Form submit callback.
 */
//function batch_form_submit($form, &$form_state) {
//// Подготавливаем данные для операций
//  $result = db_select('node', 'n')->fields('n', array('nid'))->execute();
//
//// Создаём массив с операциями.
//  foreach ($result as $row) {
//    $operations[] = array('batch_change_date', array($row->nid));
//  }
//
//  $batch = array(
//// Массив операций и их параметров
//    'operations' => $operations,
//// Функция, которая будет выполнена после окончания всех операций
//    'finished' => 'batch_finished',
//// Заголовок страницы с прогресс баром.
//// Опционально, по умолчанию t('Processing')
//    'title' => 'Обновление дат',
//// Сообщение, показываемое при инициализации.
//// Опционально, по умолчанию t('Initializing.')
//    'init_message' => 'Подготовка данных',
//// Сообщение, показывемое при выполнении операций.
//// Опционально, по умолчанию t('Completed @current of @total.')
//    'progress_message' => 'Выполнено @current из @total.',
//// Сообщение показываемое при ошибке выполнения операции.
//// Опционально, по умолчанию t('An error has occurred.')
//    'error_message' => 'Произошла ошибка.',
//  );
//
//  batch_set($batch);
//
//// Если Batch API используется не из _submit функции,
//// то дополнительно нужно вызвать batch_process();
//}
//
///**
// * Batch process callback.
// */
//function batch_change_date($nid, &$context) {
//// Производим манипуляции над нодами
//  $node = node_load($nid);
//  $node->created = time();
//  node_save($node);
//
//// Эта информация будет доступна в mymodule_batch_finished
//  $context['results']['titles'][] = $node->title;
//// Сообщение выводимое под прогресс-баром после окончания текущей операции
//  $context['message'] = 'Обновлена дата у материала <em>' . check_plain($node->title) . '</em>';
//}
//
///**
// * Batch finish callback.
// */
//function mymodule_batch_finished($success, $results, $operations) {
//  if ($success) {
//    drupal_set_message('Обновлена дата у ' . count($results['titles']) . ' материалов:' . theme('item_list', array('items' => $results['titles'])));
//  }
//  else {
//    drupal_set_message('Завершено с ошибками.', 'error');
//  }
//}