<?php

namespace App\Http\Controllers;

use App\Models\Listing;
use Illuminate\Http\Request;
use Illuminate\Validation\Rule;

class ListingController extends Controller
{
    // Show all listings.
    public function index()
    {
        return view('listings.index', [
            // 'listings' => Listing::all()
            'listings' => Listing::latest()->filter(request(['tag', 'search']))->paginate(5)
        ]);
    }

    // Show a single listing.
    public function show(Listing $listing)
    {
        return view('listings.show', [
            'listing' => $listing
        ]);
    }

    // Show Create Form.
    public function create() {
        return view('listings.create');
    }

    // Store Listing Data.
    public function store(Request $request) {
        // Function storage() saves in folder storage/app/
        //dd($request->all());
        $formFields = $request->validate([
            'title' => 'required',
            'company' => ['required', Rule::unique('listings', 'company')],
            'location' => 'required',
            'website' => 'required',
            'email' => ['required','email'],
            'tags' => 'required',
            'description' => 'required'
        ]);

        // Check if image was uploaded.
        if($request->hasFile('logo')) {
            $formFields['logo'] = $request->file('logo')->store('logos','public');
        }

        //dd($request->file('logo')->store('logos','public'));
        Listing::create($formFields);

        //Session::flash('message', 'Listing created!');

        return redirect('/')->with('message', 'Listing created successfully!');
    }
}
