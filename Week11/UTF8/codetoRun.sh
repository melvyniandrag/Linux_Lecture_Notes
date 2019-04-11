echo -e "\xf0\x9F\x98\x81"
echo -e "\xf0\x9F\x98\x81" > smile
awk '/\xf0\x9f\x98\x81/' smile
awk '/\360\237\230\201/ {print "my action here"}' smile
hexdump smile 
hexdump -b smile 
hexdump -C smile
xxd smile  # what data format is given by xxd by default? How to change it?
# how to use xxd to reverse the format?
