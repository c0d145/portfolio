<x-layout>
    <x-card class="p-10 max-w-lg mx-auto mt-24">
        <header class="text-center">
            <h2 class="text-2xl font-bold uppercase mb-1">
                Edit Tweet
            </h2>
            <p class="mb-4">Edit {{$tweet->title}}</p>
        </header>
    
        <form method="POST" action="/tweets/{{$tweet->id}}" enctype="multipart/form-data">
            @csrf
            @method('PUT')
    
            <div class="mb-6">
                <label for="title" class="inline-block text-lg mb-2">Tweet Title</label>
                <input type="text" class="border border-gray-200 rounded p-2 w-full" name="title"
                    placeholder="Put your tweet title in here!" value="{{$tweet->title}}"/>
    
                @error('title')
                    <p class="text-red-500 text-xs mt-1">{{$message}}</p>
                @enderror
            </div>
    
            <div class="mb-6">
                <label for="tags" class="inline-block text-lg mb-2">
                    Tags (Comma Separated)
                </label>
                <input type="text" class="border border-gray-200 rounded p-2 w-full" name="tags" value="{{$tweet->tags}}"
                    placeholder="Example: lifestyle, politics, hobbies, etc" />
                
                @error('tags')
                    <p class="text-red-500 text-xs mt-1">{{$message}}</p>
                @enderror
            </div>
    
            <div class="mb-6">
                <label for="description" class="inline-block text-lg mb-2">
                    Tweet Text
                </label>
                <textarea class="border border-gray-200 rounded p-2 w-full" name="description" rows="10"
                    placeholder="Include tasks, requirements, salary, etc">{{$tweet->description}}</textarea>
                
                @error('description')
                    <p class="text-red-500 text-xs mt-1">{{$message}}</p>
                @enderror
            </div>
    
            <div class="mb-6">
                <button class="bg-laravel text-white rounded py-2 px-4 hover:bg-black">
                    Edit Tweet
                </button>
    
                <a href="/" class="text-black ml-4"> Back </a>
            </div>
        </form>
    </x-card>
    </x-layout>