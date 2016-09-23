<div id="ds_form_title">
  Sign Up for Free
</div>

<div id="ds_form_names">
  <?php print render($form['first_name']); ?>
  <?php print render($form['last_name']); ?>
</div>
<div id="ds_form_email">
  <?php print render($form['email']); ?>
  <?php print render($form['email_repeat']); ?>
</div>
<div id="ds_form_submit">
  <?php print render($form['submit_button']); ?>
</div>
<?php print drupal_render_children($form); ?>