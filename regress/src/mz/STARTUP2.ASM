
;--- testing .STARTUP and .EXIT directives for SMALL
;--- no error expected

    .286
    .model small
	.stack 100h

	.code

	.startup
	.exit 1+2+3

	END
