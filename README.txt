
**********************   WEB CRAWLER   **************************

******************  C Programming Language  *********************

********************  Operating Systems  ************************

>>Description:

	This is the End Semester project for CS-330: Operating System. 
	We have implemented this using C programming language.

	>>Motivation:

		Our main motivation was to implement the Operating System concepts.

	>>Build With:

		. C programming language

	>>Features:

		. CLI (Command Line Interface).
		. Crawl a website and extract all urls.
		. Filters out those urls which do not belong to same domain.
		. Provides the opportunity to pause/resume the crawling process.
		. Stores results to files.
		. User can crawl an existing unfinished crawling project.

>>Tools Required:

	. Linux Operating system.
	. libcurl Package
	. libtidy Package
	. gcc compiler

>>Installation:
	
	. First of all install the libcurl package
		~ sudo apt-get install libcurl4-openssl-dev

	. Now install libtidy package
		~ sudo apt-get install libtidy-dev

	. Paste all the .c and .h files along with Makefile in a single directory.

	. Open terminal into same directory and type following command:
		~ make
	. All the object files (.o) and executable file named "crawler" will be generated into same directory.
	
>>Usage:
	
	. First of all run the created executable file named "crawler"
		~ ./crawler
	
	. Now your crawler is up and running.
	
	. Crawler will be asking for some inputs and options.

	. You can choose appropriate options and provide relevant inputs to get perfect results. Thanks!

>>Contributors:

	Muhammad Bilal 219241 BSCS-8B

	Ahmad Dawood   266705 BSCS-8B

	Dhanesh Kumar  262405 BSCS-8B

>>License:

	@All copywrites reserved. Copying the source code is highly discouraged and will be considered as
	plagiarism.
