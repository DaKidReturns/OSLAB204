#! /bin/bash
#Created by Rohit Karunakaran

show_help()
{
    echo "
    Scientific calcualtor implementaion using bash.
    Enter 'help' to show this menu.
    Enter quit to exit

        a+b     Add a and b
        a-b     Subtract b from a
        a*b     Multiply a and b
        a/b     Divide a and b
        a^b     Exponential, Raise a to the power of b
        a%b     Modulo operation, Remainder of a/b

        sin(x)    sine of x, x is in radians
        cos(x)    cosine of x, x in radians
        log(x)    natural log of x
        exp(x)    raise e to the power of x
        sqrt(x) Find the square root of x" 
}

show_help

echo -n "Sci_calculator>> "

while read command args
do
    case $command
        in
        quit|exit)   exit 0             ;;
        help)        show_help          ;;
        *)           awk "BEGIN{print $command}" ;;
    esac

    echo -n "Sci_calculator>> "
done
