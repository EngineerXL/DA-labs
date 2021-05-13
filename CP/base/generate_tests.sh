cd tests
for (( t = 1; t <= 99; t++ ));
do
	rm -rf "$t.in" "$t.out"
	touch "$t.in" "$t.out"
done
