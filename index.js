import Travis from 'travis-ci';
import Promise from 'bluebird';
import { SerialPort } from 'serialport';

const OWNER_NAME = 'Zhigalov';
const REPO_NAME = 'frontend-fellows-test';
const PORT = '/dev/tty.usbmodem1421';

const travis = new Travis({ version: '2.0.0' });
const serialPort = new SerialPort(PORT, { baudrate: 9600 }, false);

const getBuilds = travis.repos(OWNER_NAME, REPO_NAME).builds().get;
const getBuildsAsync = Promise.promisify(getBuilds);
const openSerialAsync = new Promise((resolve, reject) =>
    serialPort.open(err => err ? reject(err) : setTimeout(resolve, 1000))
);
const sleepTenSeconds = () => new Promise(resolve => setTimeout(resolve, 10000));

async function getLastBuildState() {
    const res = await getBuildsAsync();
    const [lastBuild] = res.builds;

    return lastBuild && lastBuild.state;
}

(async () => {
    await openSerialAsync;

    while (true) {
        const state = await getLastBuildState();

        if (state) {
            serialPort.write(`${state}`);
            console.log(`${new Date()}: ${state}`);
        }

        await sleepTenSeconds();
    }
})();
