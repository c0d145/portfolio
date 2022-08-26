<?php
    namespace App\Models;
    class Listing{
        public static function all() {
            return [
                [
                    'id' => 1,
                    'title' => 'Listing One',
                    'description' => 'This is listing number one.'
                ], 
                [
                    'id' => 2,
                    'title' => 'Listing One',
                    'description' => 'This is listing number two.'
                ]
                ];
        }
        public static function find($id) {
            $listings = self::all();
            foreach ($listings as $listing) {
                if($listing['id'] == $id) {
                    return $listing;
                }
            }
        }
    }
 