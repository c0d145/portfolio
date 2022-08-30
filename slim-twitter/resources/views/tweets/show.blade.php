<x-layout>
    <a href="/" class="inline-block text-black ml-4 mb-4"><i class="fa-solid fa-arrow-left"></i> Back
    </a>
    <div class="mx-4">
        <x-card class="p-10">
            <div class="flex flex-col items-center justify-center text-center">
                <img class="w-12 h-12 mr-6 mb-6"
                    src="{{ asset('/images/no-image.png') }}"    
                    {{-- TODO: Load avatar of user who did the tweet. --}}
                    {{-- src="{{ $tweet->logo ? asset('storage/' . $tweet->logo) : asset('/images/no-image.png') }}" --}}
                    alt="" />

                <h3 class="text-2xl mb-2">{{ $tweet->title }}</h3>
                {{-- <div class="text-xl font-bold mb-4">{{ $tweet->company }}</div> --}}

                <x-tweet-tags :tagsCSV="$tweet->tags" />
                <br>
                {{-- <div class="text-lg my-4">
                    <i class="fa-solid fa-location-dot"></i> {{ $tweet->location }}
                </div> --}}
                <div class="border border-gray-200 w-full mb-6"></div>
                <div>
                    <h3 class="text-3xl font-bold mb-4">
                        Tweet Text
                    </h3>
                    <div class="text-lg space-y-6">
                        {{ $tweet->description }}
                    </div>
                </div>
            </div>
        </x-card>
        <x-card clas="mt-4 p-2 flex space-x-6">
            <a href="/tweets/{{ $tweet->id }}/edit"><i class="fa-solid fa-pencil"></i> Edit</a>
            <form method="POST" action="/tweets/{{ $tweet->id }}">
                @csrf
                @method('DELETE')
                <button class="text-red-500"><i class="fa-solid fa-trash"></i> Delete</button>
            </form>
        </x-card>
    </div>
</x-layout>