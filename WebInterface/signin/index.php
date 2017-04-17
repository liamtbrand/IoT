<?php
require '../includes.php';
?>

<style type="text/css">
    body {
      background-color: #DADADA;
    }
    body > .grid {
      height: 100%;
    }
    .image {
      margin-top: -100px;
    }
    .column {
      max-width: 450px;
    }
    .sign-in-modal{
      max-width: 450px;
    }
  </style>

<div class="ui middle aligned center aligned grid">
  <div class="column">
    <h2 class="ui blue image header">
      <img src="/assets/images/logo.png" class="image">
      <div class="content">
        Sign in to your account
      </div>
    </h2>

    <div class="ui stacked segment">

      <h4 class="ui horizontal divider header">
        <i class="sign in icon"></i>
        Sign in with
      </h4>

      <p>
        <button class="ui fluid large facebook button">
          <i class="facebook icon"></i>
          Facebook
        </button>
      </p>
      <p>
        <button class="ui fluid large google plus button">
          <i class="google plus icon"></i>
          Google
        </button>
      </p>

      <div class="ui horizontal divider">
        OR
      </div>

      <button class="ui fluid large blue button" id="signin">
        Sign in as Developer
      </button>

    </div>

    <div class="ui message">
      New to us? <a href="/signup">Sign up</a>
    </div>
  </div>
</div>

<script>

$(document).ready(function() {
  /*
  $('.ui.form')
    .form({
      fields: {
        email: {
          identifier  : 'email',
          rules: [
            {
              type   : 'empty',
              prompt : 'Please enter your e-mail'
            },
            {
              type   : 'email',
              prompt : 'Please enter a valid e-mail'
            }
          ]
        }
      }
    })
  ;*/

  $('#signin').click(function(){
    window.location = "/home";
  });

});

</script>
