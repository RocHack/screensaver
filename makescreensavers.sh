#!/bin/bash

i=1
while read line; do
    cat > programs/"Program$i.java" <<- EOF

public class Program {
    public static void main(String[] args) {
        System.out.println("$line");
    }
}
EOF
i=`expr $i + 1`
done < programs/sayings.txt


