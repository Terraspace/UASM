
    .x64
    .model flat
    .code

    option evex:1

repe scasb
repz scasw
repe scasq

rep scasb
rep scasd
rep scasq

repe cmpsb
repz cmpsd
repe cmpsq

rep cmpsb
rep cmpsd
rep cmpsq

    end
