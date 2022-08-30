@props(['tweet'])

<x-card>
    <div class="flex">
        <img
            class="hidden w-12 h-12 mr-6 md:block"
            src="{{ asset('/images/no-image.png') }}"    
                    {{-- TODO: Load avatar of user who did the tweet. --}}
                    {{-- src="{{ $tweet->logo ? asset('storage/' . $tweet->logo) : asset('/images/no-image.png') }}" --}}
            alt=""
        />
        <div>
            <h3 class="text-2xl">
                {{-- <a href="\tweets/{{$tweet->id}}">{{$tweet->title}}</a> --}}
                {{$tweet->title}}
            </h3>
            {{-- <div class="text-xl font-bold mb-4">{{$tweet->company}}</div> --}}
            {{-- {{$user_name}}  --}}
            Posted: {{$tweet->created_at}}
            <x-tweet-tags :tagsCSV="$tweet->tags"/>
            {{-- <div class="text-lg mt-4">
                <i class="fa-solid fa-location-dot"></i> {{$tweet->location}}
            </div> --}}

            <p>
                {{$tweet->description}}
            </p>
            {{-- <a href="/tweets/{{ $tweet->id }}/edit"><i class="fa-solid fa-pencil"></i> Edit</a>
            <form method="POST" action="/tweets/{{ $tweet->id }}">
                @csrf
                @method('DELETE')
                <button class="text-red-500"><i class="fa-solid fa-trash"></i> Delete</button>
            </form> --}}
        </div>
    </div>
</x-card>