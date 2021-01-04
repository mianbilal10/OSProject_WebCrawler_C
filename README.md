# Crawling Spider

A web crawler to extract urls from web implemented in C.

## Description

### Build With:

`C programming` language

###Features:

	1. CLI (Command Line Interface).
	2. Crawl a website and extract all urls.
	3. Filters out those urls which do not belong to same domain.
	4. Provides the opportunity to pause/resume the crawling process.
	5. Stores results to files.
	6. User can crawl an existing unfinished crawling project.

## Getting Started

### Dependencies

To run this crawler you need following pre-requisites:
* Linux Operating system.
* libcurl Package
* libtidy Package
* gcc compiler

### Installing

* First of all install the libcurl package
	```
	sudo apt-get install libcurl4-openssl-dev
	```

* Now install libtidy package
	```
	sudo apt-get install libtidy-dev
	```

* Paste all the .c and .h files along with Makefile in a single directory.

* Open terminal into same directory and type following command:
	```
	make
	```
* All the object files (.o) and executable file named "crawler" will be generated into same directory.

### Usage

* First of all run the created executable file named "crawler"
	```
	./crawler
	```
	
* Now your crawler is up and running.
	
* Crawler will be asking for some inputs and options.

* You can choose appropriate options and provide relevant inputs to get perfect results.

* To pause the crawling process
	```
	Ctrl + F
	```
* To Resume the crawling process
	```
	Ctrl + Q
	```

* To terminate the crawling process
	```
	Ctrl + C
	```
	```
	NOTE: Your progress will be saved to project folder even if you terminate the program.
	```

## Authors

Muhammad Bilal  
[@mianbilal10](https://github.com/mianbilal10)

Ahmad Dawood
[@mianbilal10](https://github.com/AhmadDawood225)

Dhanesh Kumar Meghwar

## Version

* 1.0
    * Initial Release

## License

All copywrites reserved. Anyone can contribute to the project and illegal use of this crawler is not permitted and highly discouraged.
