<?php

namespace App\Http\Controllers;

use App\Models\Tweet;
use Illuminate\Http\Request;
use Illuminate\Validation\Rule;

class TweetController extends Controller
{
    // Show all tweets.
    public function index()
    {
        return view('tweets.index', [
            // 'tweets' => Tweet::all()
            'tweets' => Tweet::latest()->filter(request(['tag', 'search']))->paginate(5)
        ]);
    }

    // Show a single tweet.
    public function show(Tweet $tweet)
    {
        return view('tweets.show', [
            'tweet' => $tweet
        ]);
    }

    // Show create form.
    public function create() {
        return view('tweets.create');
    }

    // Store tweet data.
    public function store(Request $request) {
        // Function storage() saves in folder storage/app/
        //dd($request->all());
        $formFields = $request->validate([
            'title' => 'required',
            // 'company' => ['required', Rule::unique('tweets', 'company')],
            // 'location' => 'required',
            // 'website' => 'required',
            // 'email' => ['required','email'],
            'tags' => 'required',
            'description' => 'required'
        ]);

        // Check if image was uploaded.
        // if($request->hasFile('logo')) {
        //     $formFields['logo'] = $request->file('logo')->store('logos','public');
        // }

        $formFields['user_id'] = auth()->id();

        //dd($request->file('logo')->store('logos','public'));
        Tweet::create($formFields);

        //Session::flash('message', 'Tweet created!');

        return redirect('/')->with('message', 'Tweets created successfully!');
    }

    // Show Edit Form
    public function edit(Tweet $tweet) {
        return view('tweets.edit', ['tweet' => $tweet]);
    }

    // Update tweet data.
    public function update(Request $request, Tweet $tweet) {
        // Function storage() saves in folder storage/app/
        //dd($request->all());
        $formFields = $request->validate([
            'title' => 'required',
            // 'company' => ['required'],
            // 'location' => 'required',
            // 'website' => 'required',
            // 'email' => ['required', 'email'],
            'tags' => 'required',
            'description' => 'required'
        ]);

        // Check if image was uploaded.
        if($request->hasFile('logo')) {
            $formFields['logo'] = $request->file('logo')->store('logos','public');
        }

        //dd($request->file('logo')->store('logos','public'));
        $tweet->update($formFields);

        //Session::flash('message', 'Tweet created!');

        return back()->with('message', 'Tweet updated successfully!');
    }

    // Delete Tweet
    public function destroy(Tweet $tweet) {
        $tweet->delete();
        return redirect('/')->with('message', 'Tweet deleted successfully!' );
    }

    // Manage tweets
    public function manage() {
        return view('tweets.manage', ['tweets' => auth()->user()->tweets()->get()]);
    }
}
