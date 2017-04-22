
<?php
require '../includes.php';
require '../menu.php';
?>

<center>
    <div class="ui segment column">

      <div class="ui slider checkbox">
          <input name="newsletter" type="checkbox">
          <label>Liam's Room</label>
      </div>

      <div class="ui divider"></div>

      <div class="ui segment">
        <div class="ui toggle checkbox">
          <input name="public" type="checkbox" id="main-light">
          <label>Main light</label>
        </div>
      </div>
    </div>
</center>

<script src="/hub.js"></script>
<script>

  var hub = new Hub("192.168.1.4",9999);

  $(document).ready(function(){

    console.log('test');
    $("#main-light").change(function() {
      if(this.checked) {
        // Do stuff
        hub.sendMessage("LIGHT:ON");
      }else{
        // Do other stuff
        hub.sendMessage("LIGHT:OFF");
      }
    });
  });
</script>
