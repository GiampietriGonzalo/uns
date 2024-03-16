<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateListsTable extends Migration{

    public function up(){
        Schema::create('user_lists', function (Blueprint $table) {
            $table->bigIncrements('id');
            $table->string('listName');
			$table->unsignedInteger('userId');
			$table->boolean('public')->default(false);
            $table->timestamps();
        });
    }
    public function down(){
        Schema::dropIfExists('lists');
    }
}
