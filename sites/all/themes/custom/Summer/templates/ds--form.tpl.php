<div id="ds_form">
  <div id="ds_form_title">
    Sign Up for Free
  </div>

  <div id="ds_form_names">
    <?php print render($form['first_name']); ?>
    <?php print render($form['last_name']); ?>
  </div>
  <div id="ds_form_gender">
    <?php print render($form['gender']); ?>
  </div>
  <div id="ds_form_email">
    <?php print render($form['male_age']); ?>
    <?php print render($form['email']); ?>
  </div>

  <div id="ds_form_country">
    <?php print render($form['country']); ?>
    <?php print render($form['region']); ?>
  </div>

  <div id="ds_form_friend">
    <?php print render($form['subscribe_friend']); ?>
    <?php print render($form['friend_email']); ?>
  </div>

  <div id="ds_form_submit">
    <?php print render($form['submit_button']); ?>
  </div>
  <?php print drupal_render_children($form); ?>
</div>
