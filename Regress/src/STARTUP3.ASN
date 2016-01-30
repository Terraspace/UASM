
;--- testing .STARTUP and .EXIT directives for SMALL + FARSTACK
;--- no error expected

    .286
    .model small, farstack
	.stack 100h

	.code

	.startup
	.exit 1+2+3

	END
