
;--- testing .STARTUP and .EXIT directives for TINY
;--- no error expected

    .286
    .model tiny

	.code

	.startup
	.exit 1+2+3

	END
