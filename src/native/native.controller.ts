import { Controller, Get, Param, ParseIntPipe, Post, Body, HttpException, HttpStatus, Put } from '@nestjs/common';
import { NativeService } from './native.service';

@Controller('native')
export class NativeController {
  constructor(private readonly nativeService: NativeService) {}

  @Get('start-loops')
  startLoops(): { message: string } {
    const message = this.nativeService.startLoops();
    return { message };
  }

  @Get('iteration/:loopNumber')
  getIteration(@Param('loopNumber', ParseIntPipe) loopNumber: number): {
    iteration: number;
    threadId: string;
    pid: number;
  } {
    return this.nativeService.getIteration(loopNumber);
  }

  @Get('pids')
  getPIDs(): number[] {
    return this.nativeService.getPIDs();
  }

  @Put('reset-iteration')
  resetIteration(@Body() body: { loopNumber: number }): string {
    try {
      this.nativeService.resetIteration(body.loopNumber);
      return 'Iteration reset';
    } catch (error) {
      throw new HttpException(
        {
          status: HttpStatus.INTERNAL_SERVER_ERROR,
          error: 'Failed to reset iteration',
        },
        HttpStatus.INTERNAL_SERVER_ERROR,
      );
    }
  }

  @Post('pause/:loopNumber')
  pauseIteration(@Param('loopNumber', ParseIntPipe) loopNumber: number): { message: string } {
    const message = this.nativeService.pauseIteration(loopNumber);
    return { message };
  }

  @Post('resume/:loopNumber')
  resumeIteration(@Param('loopNumber', ParseIntPipe) loopNumber: number): { message: string } {
    const message = this.nativeService.resumeIteration(loopNumber);
    return { message };
  }


}
