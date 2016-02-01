how to build:

gcc -o suid suid.c && suid chown root:wheel suid && suid chmod 4750 suid

gcc -o super super.c && suid setcap cap_setuid+ep super && chmod 750 super

gcc -o pls pls.c -lcap && suid setcap cap_dac_override+ip pls && chmod 750 pls
