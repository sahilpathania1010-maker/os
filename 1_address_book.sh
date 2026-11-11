#!/bin/bash
# Run: bash 1_address_book.sh
# Each record: Name Phone City  (type the name as one word)

file="address.txt"

while true
do
    echo ""
    echo "1.Create  2.View  3.Insert  4.Delete  5.Modify  6.Exit"
    read -p "Enter choice: " ch

    case $ch in
    1)  > $file
        echo "Address book created" ;;

    2)  echo "Name Phone City"
        cat $file ;;

    3)  read -p "Name: " name
        read -p "Phone: " phone
        read -p "City: " city
        echo "$name $phone $city" >> $file
        echo "Record inserted" ;;

    4)  read -p "Enter name to delete: " name
        grep -v "^$name " $file > temp.txt
        mv temp.txt $file
        echo "Record deleted" ;;

    5)  read -p "Enter name to modify: " name
        grep -v "^$name " $file > temp.txt
        mv temp.txt $file
        read -p "New Phone: " phone
        read -p "New City: " city
        echo "$name $phone $city" >> $file
        echo "Record modified" ;;

    6)  exit ;;

    *)  echo "Invalid choice" ;;
    esac
done
