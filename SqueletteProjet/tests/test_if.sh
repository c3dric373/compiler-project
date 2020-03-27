chmod 755 pld-wrapper.sh
python3 pld-test.py tests/Init/ | tee test-result.txt
rm -rf pld-test-output
exit $(! cat test-result.txt | grep "TEST FAIL")
