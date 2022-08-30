<?php

namespace Database\Seeders;

// use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use App\Models\User;
use App\Models\Tweet;
use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
        // \App\Models\User::factory(10)->create();

        // \App\Models\User::factory()->create([
        //     'name' => 'Test User',
        //     'email' => 'test@example.com',
        // ]);


        // Create one user with the factory with is the creator of the afterwards
        // created tweets.
        $user = User::factory()->create([
            'name' => 'Test User',
//            'password' => 'password',
            'email' => 'test@user.com'
        ]);

        // Test the factory for tweet-entries. All created entries owned by "Test User".
        Tweet::factory(6)->create([
            'user_id' => $user->id
        ]);

        // Dummy for one Tweet
        // Tweet::create([
        //     'user_id' => $user->id
        //     'title' => 'Laravel Senior Developer',
        //     'tags' => 'laravel, javascript',
        //     'description' => 'Lorem ipsum dolor sit amet consectetur adipisicing elit. Ipsam minima et illo reprehenderit quas possimus voluptas repudiandae cum expedita, eveniet aliquid, quam illum quaerat consequatur! Expedita ab consectetur tenetur delensiti?'
        // ]);
    }
}
