<?php
/**
* Custom subscription form.
*/
function new_batch_change_name_form($form, &$form_state) {

$form['old_first_name'] = [
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

$form['new_first_name'] = [
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

$form['submit_button'] = array(
'#type' => 'submit',
'#value' => t('Change!'),
);
return $form;
}

/**
* Implement hook_form_submit().
* @param $form
* @param $form_state
*/
function new_batch_change_name_form_submit($form, &$form_state) {



drupal_set_message(t('Success!'));
}

