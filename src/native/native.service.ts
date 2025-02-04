import { Injectable } from '@nestjs/common';
const addon = require('../../build/Release/addon.node');

@Injectable()
export class NativeService {
  private threadCount = 0;
  private readonly maxThreads = 1;
  private isBlocked = false;

  startLoops(): string {
    if (this.isBlocked) {
      return 'Procesos ya iniciados';
    }

    if (this.threadCount >= this.maxThreads) {
      this.isBlocked = true;
    }

    this.threadCount++;
    addon.startLoops();
    return `Thread started`;
  }

  getIteration(loopNumber: number): { iteration: number, threadId: string, pid: number } {
    return addon.getIteration(loopNumber);
  }

  getPIDs(): number[] {
    return addon.getPIDs();
  }
}