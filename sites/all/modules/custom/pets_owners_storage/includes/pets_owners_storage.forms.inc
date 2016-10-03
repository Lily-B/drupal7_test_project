<?php

/**
 * Custom Pets owner's form.
 */
function pets_owners_storage_form($form, &$form_state) {

  $form['p_o'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pets owners data'),
  );

  $form['p_o']['first_name'] = array(
    '#prefix' => '<div id="fName">',
    '#suffix' => '</div>',
    '#title' => t('First Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => array(
      'placeholder' => t('First Name '),
    ),
    '#size' => 20,
    '#maxlength' => 20,
    '#rules' => array(
      'alpha_dash',
      array(
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      ),
    ),
  );

  $form['p_o']['last_name'] = array(
    '#prefix' => '<div id="lName">',
    '#suffix' => '</div>',
    '#title' => t('Last Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => array(
      'placeholder' => t('Last Name '),
    ),
    '#size' => 20,
    '#maxlength' => 20,
    '#rules' => array(
      'alpha_dash',
      array(
        'rule' => 'length[1,20]',
        'error' => t('Please, enter a shorter than 20 char name.')
      )
    ),
  );

  $form['p_o']['email'] = array(
    '#title' => t('Email'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#attributes' => array(
      'placeholder' => t('Email Address *'),
    ),
    '#rules' => array(
      array(
        'rule' => 'email',
        'error' => t('Please, enter a valid email.')
      ),
      array(
        'rule' => 'length[3,30]',
        'error' => t('Please, enter a shorter than 30 char email.')
      )
    ),
  );

  $id = arg(2);
  if (isset($id)) {
    if (user_access('access all pets owners table')) {
      $owner = find_pet_owner_by_id($id);
      $form['p_o']['first_name']['#default_value'] = $owner->first_name;
      $form['p_o']['last_name']['#default_value'] = $owner->last_name;
      $form['p_o']['email']['#default_value'] = $owner->email;
    }
    else {
      drupal_access_denied();
    };
  }

  $form['po']['submit_button'] = array(
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
  $entry = array(
    'first_name' => $new_fname,
    'last_name' => $new_lname,
    'email' => $new_email,
  );

  if (isset($id)) {
    if (user_access('access all pets owners table')) {
      if (edit_pets_owner_in_db($id, $entry)) {
        drupal_set_message(t('Pets Owners data was edited successfully!'));
        drupal_goto('pets_owners_storage/pets_owners_page');
      }
      else {
        drupal_set_message(t('Editing failed!'), 'error');
      }
    }
    else {
      drupal_access_denied();
    };
  }
  else {
    if (add_new_pets_owner_in_db($entry)) {
      drupal_set_message(t('Pets owners data was added successfully!'));
    }
    else {
      drupal_set_message(t('Adding failed!'), 'error');
    };
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

  $new_email = trim($form_state['values']['email']);
  $id = arg(2);
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


