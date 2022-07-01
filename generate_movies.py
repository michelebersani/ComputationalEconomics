import argparse
import numpy as np
import matplotlib.animation as animation
import matplotlib.pyplot as plt


def runlength_decode(encoded_seq, N):
	seq = np.zeros(N * N, dtype=int)
	next_val = bool(encoded_seq[0])
	left_bound = 0

	for digit in encoded_seq[1:]:
		if next_val:
			seq[left_bound:left_bound+digit] = 1
		left_bound = left_bound+digit
		next_val = not next_val

	return seq.reshape((N, N))


def update(frameNum, img, grids, N):
	# update data
	img.set_data(255*grids[frameNum].reshape((N, N)))
	img.set_clim(vmin=0, vmax=255)
	return img,


# main() function
def main():
	parser = argparse.ArgumentParser(description="Runs Conway's Game of Life simulation.")

	# add arguments
	parser.add_argument('--inputPath', dest='inputPath', required=True)
	parser.add_argument('--savePath', dest='savePath', required=False)
	args = parser.parse_args()

	N = 100
	grids = [np.ones((N, N))]
	with open(args.inputPath) as file:
		for line in file:
			grids.append(runlength_decode([int(number) for number in line.split(', ')], N))

	# set up animation
	# For the saved animation the duration is going to be frames * (1 / fps) (in seconds)
	# For the display animation the duration is going to be frames * interval / 1000 (in seconds)
	fig, ax = plt.subplots()
	img = ax.imshow(grids[0] * 255, interpolation='nearest')
	ani = animation.FuncAnimation(
		fig,
		update,
		fargs=(img, grids, N),
		frames=len(grids),
		interval=100,
		save_count=50
	)

	if args.savePath:
		ani.save(args.savePath, fps=10, extra_args=['-vcodec', 'libx264'])

# call main
if __name__ == '__main__':
	main()
