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

        s(x)    sine of x, x is in radians
        c(x)    cosine of x, x in radians
        l(x)    natural log of x
        e(x)    raise e to the power of x
        sqrt(x) Find the square root of x" 
}

calculate(){
    if [[ $1 = *'%'* ]]
    then
        scale=0
        echo "scale=${scale};${1}" | bc -l -q
    else
        scale=4
        echo "scale=${scale};${1}" | bc -l -q | awk '{printf "%.4f", $0}'
        echo ""
    fi


    #if [ ${1:0:1} = 's' | ${1:0:1} = 'c' | ${1:0:1} = 'l' | ${1:0:1} = 'e' ]
    #then
        
    #fi
}

show_help

echo -n "Sci_calculator>> "

while read command args
do
    case $command
        in
        quit|exit)   exit 0             ;;
        help)        show_help          ;;
        *)           calculate $command ;;
    esac

    echo -n "Sci_calculator>> "
done
