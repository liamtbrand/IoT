<?php
require '../includes.php';
require '../menu.php';
?>

<div class="ui raised very padded text container segment">
  <div class="ui form">
    <div class="ui segment">
      <h4 class="ui dividing header">Account Details</h4>

      <div class="ui fields">
        <div class="ui required field">
          <label>Username</label>
          <input placeholder="Username" type="text" id="username">
        </div>

        <div class="ui required field">
          <label>Primary email</label>
          <input placeholder="example@example.com" type="text" id="primary-email">
        </div>

      </div>

      <div style="text-align:right;">
        <button class="ui button">Save</button>
      </div>
    </div>

    <div class="ui segment">
      <h4 class="ui dividing header">Authentication Details</h4>

      <p>Linked accounts that can be used to sign in.</p>

      <div class="ui three fields">
        <div class="ui field">
          <button class="ui fluid large facebook button">
            <i class="facebook icon"></i>
            Facebook
          </button>
        </div>

        <div class="ui field">
          <button class="ui fluid large google plus button">
            <i class="google plus icon"></i>
            Google
          </button>
        </div>
      </div>

      <div style="text-align:right;">
        <button class="ui button">Save</button>
      </div>
    </div>

    <div class="ui segment">
      <h4 class="ui dividing header">Personal Details</h4>

      <div class="ui fields">
        <div class="ui required field">
          <label>First name</label>
          <input placeholder="First Name" type="text" id="first-name">
        </div>
        <div class="ui field">
          <label>Middle name(s)</label>
          <input placeholder="Middle Name(s)" type="text" id="middle-names">
        </div>
        <div class="ui required field">
          <label>Last name</label>
          <input placeholder="Last Name" type="text" id="last-name">
        </div>
      </div>

      <div style="text-align:right;">
        <button class="ui button">Save</button>
      </div>
    </div>
  </div>

</div>

<script>
  $(document).ready(function(){

    var username = "liamtbrand";
    var primaryEmail = "liamtbrand@gmail.com";

    var firstName = "Liam";
    var middleNames = "Tahi";
    var lastName = "Brand";

    $('#username').val(username);
    $('#primary-email').val(primaryEmail);

    $('#first-name').val(firstName);
    $('#middle-names').val(middleNames);
    $('#last-name').val(lastName);

  });
</script>
