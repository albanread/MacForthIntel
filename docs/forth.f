

: T.
  0x2020202020202020 PAD !
  PAD >R
  R> 1 + >R
  BEGIN
    DUP BASE @ MOD
    digit
    R@ C!
    R> 1 + >R
    BASE @ /
    DUP 0 =
  UNTIL
  DROP

  R>
  BEGIN
    1 -
    DUP C@ EMIT
    DUP PAD >
  WHILE
  REPEAT
  C@ EMIT
;

: . .- U. ;


: ACCEPT1
    >R  0
    BEGIN
        KEY
        DUP 10 =
        IF
            DROP R> DROP EXIT
        THEN
        DUP EMIT OVER C! 1 + SWAP 1 + SWAP
        R@ OVER >
    UNTIL
    DROP R> DROP
;

\ this is garbage, it pokes bytes into the wrong places
: ACCEPT2
    >R
    DUP
    0
    BEGIN
        KEY
        DUP 10 = IF DROP R> DROP EXIT THEN
        DUP EMIT
        OVER OVER + C!
        1 +
        R@ OVER >
    UNTIL
    DROP R> DROP ;


    : ACCEPT

    		DUP 2>R
    		BEGIN
    			KEY DUP 10 = IF
                 2DROP
     			     2R> -
    				EXIT
    			THEN
    			DUP EMIT
    			SWAP TUCK C! 1 +
      			R> 1 - >R
    		R@ 0 = UNTIL
    		DROP
    		 2R> -

    ;