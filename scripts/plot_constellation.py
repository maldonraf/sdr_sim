import subprocess
import sys
import numpy as np
import matplotlib.pyplot as plt

command = ['./build/RM-MB-1/tests/data_gen', sys.argv[1]] if len(sys.argv) > 1 else ['./build/RM-MB-1/tests/data_gen']
print(f'Running command: {" ".join(command)}')
result = subprocess.run(
    command,
    capture_output=True,
    text=True
)

lines = result.stdout.strip().split('\n')
iq = np.array([list(map(float, l.split(','))) for l in lines])

plt.figure(figsize=(5,5))
plt.scatter(iq[:,0], iq[:,1], s=2, alpha=0.4)
plt.axhline(0, color='k', linewidth=0.5)
plt.axvline(0, color='k', linewidth=0.5)
plt.title('Constellation — post-AWGN')
plt.xlabel('I'); plt.ylabel('Q')
plt.axis('equal')
plt.tight_layout()
plt.show()