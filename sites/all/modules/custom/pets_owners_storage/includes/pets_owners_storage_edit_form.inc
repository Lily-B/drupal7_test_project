<?php
/**
 * Pets owner's Editform.
 * @param $form
 * @param $form_state
 * @param $owner
 * @return mixed
 */
function pets_owners_storage_edit_form($form, &$form_state, $owner) {

  $form['#owner_id'] = $owner->id;

  $form['edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit a person entry'),
  );

  $form['edit']['first_name'] = array(
    '#prefix' => '<div id="fName">',
    '#suffix' => '</div>',
    '#title' => t('First Name'),
    '#type' => 'textfield',
    '#default_value' => $owner->first_name,
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

  $form['edit']['last_name'] = array(
    '#prefix' => '<div id="lName">',
    '#suffix' => '</div>',
    '#title' => t('Last Name'),
    '#type' => 'textfield',
    '#default_value' => $owner->last_name,
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

  $form['edit']['email'] = array(
    '#title' => t('Email'),
    '#type' => 'textfield',
    '#default_value' => $owner->email,
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

  $form['edit']['link'] = array(
    '#markup' => l(t('Delete'),
      'pets_owners_storage/delete_owner/' . $owner->id,
      array('attributes' => array('class' => 'delete-link'))),
    '#ajax' => array(
      'callback' => 'delete_callback',
    ),
    '#suffix' => '<br><br>',
  );

  $form['edit']['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Submit!'),
  );

  return $form;
}

/**
 * Callback function for pets_owners_storage_edit_form
 * @param string $id
 * @return array|mixed
 */
function pets_owners_storage_edit_form_callback($id = 'all') {
  $owner = find_pet_owner_by_id($id);
  return drupal_get_form('pets_owners_storage_edit_form', $owner);
}

/**
 * Implement hook_form_submit().
 * @param $form
 * @param $form_state
 */
function pets_owners_storage_edit_form_submit($form, &$form_state) {
  $id = $form['#owner_id'];
  $new_email = $form_state['values']['email'];
    $new_fname = $form_state['values']['first_name'];
    $new_lname = $form_state['values']['last_name'];

    $entry = array(
      'id' => $id,
      'first_name' => $new_fname,
      'last_name' => $new_lname,
      'email' => $new_email,
    );
    if (edit_pets_owner_in_db($id, $entry)) {
      drupal_set_message(t('Success!'));
      drupal_goto('pets_owners_storage/pets_owners_page');
    }
    else {
      drupal_set_message(t('No success!'), 'error');
    };
}

/**
 * Implement hook_form_validate().
 * @param $form
 * @param $form_state
 * @return bool
 */
function pets_owners_storage_edit_form_validate($form, &$form_state) {
  $id = $form['#owner_id'];
  $new_email = $form_state['values']['email'];

  if (!is_owners_email_unique($id, $new_email)) {
    form_set_error('email',t('Pets Owner with this E-mail already exists!'));
  }
}
