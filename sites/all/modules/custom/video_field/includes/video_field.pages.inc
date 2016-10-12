<?php
/**
 * @return string
 */
function video_nodes_callback() {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', array('video', 'page'))
    ->fieldCondition('field_youtube_video', 'video_controls', 1, '=');
  $result = $query->execute();
  $output = '';
  if (isset($result['node'])) {
    $items_nids = array_keys($result['node']);
    $items_with_video = entity_load('node', $items_nids);
    foreach ($items_with_video as $item) {
      foreach ($item->field_youtube_video['und'] as $video) {
        if ($video['video_controls'] == '1') {
          $output .= 'Video ';
          $output .= l(t($video['video_title']), $video['video_url'], array('attributes' => array('target' => '_blank')));
          $output .= ' in ' . $item->type . ' ' . $item->title;
          $output .= '<br>';
        }
      }
    }
  }
  return $output;
}

