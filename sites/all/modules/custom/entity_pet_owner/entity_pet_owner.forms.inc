<?php
/**
 * Form definition for adding / editing a pet owner.
 */
function pet_owner_form($form, &$form_state, $owner = NULL) {

  // ADD language variable .

  $langcode = entity_language('pet_owner', $owner);

  if (empty($langcode)) {
    $langcode = LANGUAGE_NONE;
  }
  dpm($langcode);



  $form['p_o'] = [
    '#type' => 'fieldset',
    '#title' => t('Pets owners data'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  // ADD language to form.
  $form['p_o']['language'] = array(
    '#type' => 'value',
    '#value' => $langcode,
  );

  $form['p_o']['first_name'] = [
    '#prefix' => '<div id="fName">',
    '#suffix' => '</div>',
    '#title' => t('First Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => [
      'placeholder' => t('First Name '),
    ],
    '#size' => 20,
    '#maxlength' => 20,
//    '#rules' => [
//      'alpha',
//      [
//        'rule' => 'length[1,20]',
//        'error' => t('Please, enter a shorter than 20 char name.')
//      ],
//    ],
  ];

  $form['p_o']['last_name'] = [
    '#prefix' => '<div id="lName">',
    '#suffix' => '</div>',
    '#title' => t('Last Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => [
      'placeholder' => t('Last Name '),
    ],
    '#size' => 20,
    '#maxlength' => 20,
//    '#rules' => [
//      'alpha',
//      [
//        'rule' => 'length[1,20]',
//        'error' => t('Please, enter a shorter than 20 char name.')
//      ]
//    ],
  ];

  $form['p_o']['birthday'] = [
    '#title' => t('Birthday'),
    '#type' => 'date',
    '#required' => TRUE,
  ];
  $format = 'Y-m-d';

  $form['p_o']['date'] = array(
    '#type' => 'date_select',
    '#title' => t('select a date'),
    '#date_format' => $format,
    '#date_label_position' => 'within',
  );


  $form['p_o']['pet'] = [
    '#title' => t('Select Pet category'),
    '#type' => 'select',
    '#options' => get_all_terms_of_vocab('pets'),
    '#required' => TRUE,
  ];

  $form['p_o']['email'] = [
    '#title' => t('Email'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => [
      'placeholder' => t('Email Address *'),
    ],
//    '#rules' => [
//      [
//        'rule' => 'email',
//        'error' => t('Please, enter a valid email.')
//      ],
//      [
//        'rule' => 'length[3,30]',
//        'error' => t('Please, enter a shorter than 30 char email.')
//      ]
//    ],
  ];

  $form['p_o']['city'] = [
    '#title' => t('City'),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#attributes' => [
      'placeholder' => t('City'),
    ],
    '#rules' => [
      'alpha',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char city.')
      ],
    ]
  ];

  if (isset($owner->id)) {
    $birthday_timestamp = $owner->birthday_timestamp;
    $birthday_date = format_date($birthday_timestamp, 'custom', 'Y-m-d');
    $birthday_array = explode('-', $birthday_date);
    $new_birthday_array = [
      'year' => intval($birthday_array[0]),
      'month' => intval($birthday_array[1]),
      'day' => intval($birthday_array[2]),
    ];
    $form['p_o']['first_name']['#default_value'] = $owner->first_name;
    $form['p_o']['last_name']['#default_value'] = $owner->last_name;
    $form['p_o']['birthday']['#default_value'] = $new_birthday_array;
    $form['p_o']['pet']['#default_value'] = $owner->pet;
    $form['p_o']['email']['#default_value'] = $owner->email;
    $form['p_o']['city']['#default_value'] = $owner->city;
  }

  field_attach_form('pet_owner', $owner, $form, $form_state, $langcode);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => isset($owner->id) ? t('Update pet owner') : t('Save pet owner'),
    '#weight' => 50,
  );

  return $form;
}

/**
 * Submit handler for the project add/edit form.
 */
function pet_owner_form_submit($form, &$form_state) {
  $pet_owner = entity_ui_form_submit_build_entity($form, $form_state);
  $pet_owner->save();
  drupal_set_message(t('The pet owner: @name has been saved.', array('@name' => $pet_owner->first_name)));
  $form_state['redirect'] = 'admin/entity_pet_owner';
}
