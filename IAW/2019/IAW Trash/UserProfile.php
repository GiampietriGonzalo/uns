<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Profile extends Model{
	
    public $primaryKey = 'id';
    public $name = 'name';
    public $username = 'username';
    public $email = 'email';

    public function user(){
        return $this->belongsTo('App\User');
    }
}
