<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div
      class="field-label"<?php print $title_attributes; ?>><?php print $label ?>
      :&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>
    <?php foreach ($items as $delta => $item): ?>
      <?php if ($item['is_iframe']):?>
        <div
          class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>>
          <iframe width="<?php echo($item['width']); ?>"
                  height="<?php echo($item['height']); ?>"
                  src="<?php echo($item['url'] . '?' . $item['controls']); ?>"
                  frameborder="<?php echo($item['frameborder']); ?>"
                  allowfullscreen>
          </iframe>
        </div>
      <?php else: ?>

        <div
          class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>>
          <a href="<?php echo($item['url'] . '?' . $item['controls']); ?>"
             target="_blank">
            <?php echo($item['title']); ?>
          </a>
        </div>
      <?php endif ?>
    <?php endforeach; ?>
  </div>
</div>
