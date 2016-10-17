<?php

/**
 * Custom Pets owner's form.
 */
function pets_owners_storage_form($form, &$form_state) {

  $form['p_o'] = [
    '#type' => 'fieldset',
    '#title' => t('Pets owners data'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

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
    '#rules' => [
      'alpha_dash',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      ],
    ],
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
    '#rules' => [
      'alpha_dash',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      ]
    ],
  ];

  $form['p_o']['birthday'] = [
    '#title' => t('Birthday'),
    '#type' => 'date',
    '#required' => TRUE,
  ];
  $format = 'Y-m-d';

  $form['p_o']['date'] = array(
    '#type' => 'date_select',
    // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#title' => t('select a date'),
    '#date_format' => $format,
    '#date_label_position' => 'within',
    // See other available attributes and what they do in date_api_elements.inc
    '#date_year_range' => '-50:now',
    // Optional, used to set the year range (back 3 years and forward 3 years is the default).
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
    '#rules' => [
      [
        'rule' => 'email',
        'error' => t('Please, enter a valid email.')
      ],
      [
        'rule' => 'length[3,30]',
        'error' => t('Please, enter a shorter than 30 char email.')
      ]
    ],
  ];

  $form['p_o']['city'] = [
    '#title' => t('City'),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#attributes' => [
      'placeholder' => t('City'),
    ],
    '#rules' => [
      'alpha_dash',
      [
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char city.')
      ],
    ]
  ];

  $id = arg(2);
  if (isset($id)) {
    if (user_access('access all pets owners table')) {
      $owner = find_pet_owner_by_id($id);
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
    else {
      drupal_access_denied();
    };
  }

  $form['p_o']['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Submit!'),
  );
  return $form;

}

/**
 * Implement hook_form_submit().
 * @param $form
 * @param $form_state
 */
function pets_owners_storage_form_submit($form, &$form_state) {
  $id = arg(2);
  $new_email = trim($form_state['values']['email']);
  $new_fname = trim($form_state['values']['first_name']);
  $new_lname = trim($form_state['values']['last_name']);
  $date_fields = $form_state['values']['birthday'];
  $new_birthday = forms_date_to_timestamp($date_fields);
  $new_pet = $form_state['values']['pet'];
  $new_city = trim($form_state['values']['city']);
  $fields = array(
    'first_name' => $new_fname,
    'last_name' => $new_lname,
    'email' => $new_email,
    'birthday_timestamp' => $new_birthday,
    'pet' => $new_pet,
    'city' => $new_city,
  );

//  if (isset($id)) {
//    if (user_access('access all pets owners table')) {
//      if (edit_pets_owner_in_db($id, $entry)) {
//        drupal_set_message(t('Pets Owners data was edited successfully!'));
//        cache_clear_all('pets_owners_storage_owners_table_rows_', 'cache_pets_owners_storage', TRUE);
//        cache_clear_all('pets_owners', 'cache_views_data', TRUE);
//        drupal_goto('pets_owners_storage/pets_owners_page');
//      }
//      else {
//        drupal_set_message(t('Editing failed!'), 'error');
//      }
//    }
//    else {
//      drupal_access_denied();
//    };
//  }
//  else {
//    if (add_new_pets_owner_in_db($entry)) {
//      drupal_set_message(t('Pets owners data was added successfully!'));
//      cache_clear_all('pets_owners_storage_owners_table_rows_', 'cache_pets_owners_storage', TRUE);
//      cache_clear_all('pets_owners', 'cache_views_data', TRUE);
//    }
//    else {
//      drupal_set_message(t('Adding failed!'), 'error');
//    };
//  }

  $queue = DrupalQueue::get('pets_owners_storage_submit');
  // There is no harm in trying to recreate existing.
  $queue->createQueue();

  if (isset($id)) {
    if (user_access('access all pets owners table')) {
      //Edit
      $row = ['fields' => $fields, 'id' =>$id];
      $queue = DrupalQueue::get('pets_owners_storage_edit');
      $queue->createQueue();
      $queue->createItem($row);
      $count = $queue->numberOfItems();
      drupal_set_message(t('There are now ' . $count . ' user(s) to edit.'));
    }
    else {
      drupal_access_denied();
    };
  }
  else {
    //Add
    $queue = DrupalQueue::get('pets_owners_storage_add');
    $queue->createQueue();
    $queue->createItem($fields);
    $count = $queue->numberOfItems();
    drupal_set_message(t('There are now ' . $count . ' user(s) to add.'));
  }
}

/**
 * Implement hook_form_validate().
 * @param $form
 * @param $form_state
 * @return bool
 */
function pets_owners_storage_form_validate($form, &$form_state) {

  //Add validation to check if  required fields are not null!!!
  $date_fields = $form_state['values']['birthday'];
  $birth_timestamp = forms_date_to_timestamp($date_fields);
  $new_email = trim($form_state['values']['email']);
  $new_fname = trim($form_state['values']['first_name']);
  $new_lname = trim($form_state['values']['last_name']);
  $id = arg(2);

  if ($date_fields && ($birth_timestamp > time())) {
    form_set_error('birthday', t('Please enter a valid birthday date.'));
  }

  if (!are_owner_names_and_birth_unique($id, $new_fname, $new_lname, $birth_timestamp)) {
    form_set_error('birthday', t('Pets owner with this first name, last name and birthday already exists.'));
  }

  if (isset($id)) {


    if (!is_owners_email_unique($id, $new_email)) {
      form_set_error('email', t('Pets Owner with this E-mail already exists!'));
    };
  }
  else {
    if (email_exists_in_db($new_email)) {
      form_set_error('email', t('User with this e-mail already exists.'));
    }
  };

}

/**
 * Cron task callback ('worker callback') for 'pets_owners_storage_edit' Queue
 * @param $row
 */
function edit_pet_owner($row) {
  if (edit_pets_owner_in_db($row['id'], $row['fields'])) {
    drupal_set_message(t('Pets Owners data was edited successfully!'));
    cache_clear_all('pets_owners_storage_owners_table_rows_', 'cache_pets_owners_storage', TRUE);
    cache_clear_all('pets_owners', 'cache_views_data', TRUE);
  }
  else {
    drupal_set_message(t('Editing failed!'), 'error');
  }
}

/**
 * Cron task callback ('worker callback') for 'pets_owners_storage_add' Queue
 * @param $fields
 */
function add_pet_owner($fields) {
  if (add_new_pets_owner_in_db($fields)) {
    drupal_set_message(t('Pets owners data was added successfully!'));
    cache_clear_all('pets_owners_storage_owners_table_rows_', 'cache_pets_owners_storage', TRUE);
    cache_clear_all('pets_owners', 'cache_views_data', TRUE);
  }
  else {
    drupal_set_message(t('Adding failed!'), 'error');
  };
}




