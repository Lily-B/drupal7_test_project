<?php

/**
 * Custom form for changing names.
 */
function batch_for_pets_change_name_form($form, &$form_state) {

  $form['p_o'] = [
    '#type' => 'fieldset',
    '#title' => t('Change names'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['p_o']['old_name'] = [
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

